import json
import os
import sys

# --- Constants ---
GITHUB_WORKFLOW_STATE_FILE = ".github/workflow_state.json"
HOMEPAGE_APPS_JSON_PATH = os.path.join("homepage-app", "apps", "apps.json")
APPS_MD_PATH = "apps.md"

def read_json_file(file_path):
    if os.path.exists(file_path) and os.path.getsize(file_path) > 0:
        try:
            with open(file_path, 'r') as f:
                return json.load(f)
        except json.JSONDecodeError as e:
            print(f"::warning::Could not decode JSON from {file_path}: {e}. Returning empty data.", file=sys.stderr)
            return {}
    return {}

def write_json_file(file_path, data, indent=2):
    os.makedirs(os.path.dirname(file_path) or '.', exist_ok=True)
    with open(file_path, 'w') as f:
        json.dump(data, f, indent=indent)

def main():
    # --- Retrieve Writable Files Secrets ---
    apps_md_secret_path = os.environ.get("RWT_WRITABLE_FILE_APPS_MD")
    homepage_apps_json_secret_path = os.environ.get("RWT_WRITABLE_FILE_HOMEPAGE_APPS_JSON")
    workflow_state_secret_path = os.environ.get("RWT_WRITABLE_FILE_WORKFLOW_STATE")
    
    allowed_write_paths = set()
    if apps_md_secret_path: allowed_write_paths.add(os.path.normpath(apps_md_secret_path.strip()))
    if homepage_apps_json_secret_path: allowed_write_paths.add(os.path.normpath(homepage_apps_json_secret_path.strip()))
    if workflow_state_secret_path: allowed_write_paths.add(os.path.normpath(workflow_state_secret_path.strip()))

    def is_write_allowed(target_path):
        normalized_target_path = os.path.normpath(target_path)
        if normalized_target_path in allowed_write_paths:
            return True
        print(f"::warning::SECURITY ALERT: Attempted to write to '{target_path}', but it is not listed in allowed secrets. Write operation skipped.", file=sys.stderr)
        return False

    # --- Get current run info and force flag from environment ---
    current_workflow_run_id = os.environ.get("GITHUB_RUN_ID")
    force_upload_from_find_apps = os.environ.get("FORCE_APPS_JSON_UPLOAD_FLAG") == "true"

    print(f"::debug::FORCE_APPS_JSON_UPLOAD_FLAG received: {force_upload_from_find_apps}")

    # --- Data Collection Logic (unchanged) ---
    app_data_from_find_apps_json = os.environ.get("APP_DATA_FROM_FIND_APPS")
    if not app_data_from_find_apps_json:
        print("::error::APP_DATA_FROM_FIND_APPS environment variable is missing. It should be provided by the 'find_apps' job.", file=sys.stderr)
        sys.exit(1)
    try:
        app_details_list = json.loads(app_data_from_find_apps_json)
    except json.JSONDecodeError:
        print(f"::error::Failed to parse JSON from APP_DATA_FROM_FIND_APPS: {app_data_from_find_apps_json}", file=sys.stderr)
        sys.exit(1)

    apps_for_md_content = []
    apps_for_json_data = []

    for app_info in app_details_list:
        app_name = app_info.get("name")
        heroku_app_name = app_info.get("herokuAppName")
        app_url = app_info.get("url")
        if not app_name or not app_url or not heroku_app_name:
            print(f"::warning::Skipping entry due to missing data in app_info: {app_info}.", file=sys.stderr)
            continue
        apps_for_md_content.append(f"* **{app_name}:** [{heroku_app_name}]({app_url})")
        apps_for_json_data.append(app_info)

    # --- Prepare apps.md Content (unchanged) ---
    md_header = "# 🚀 Deployed Applications\n\n"
    md_intro = "This file lists the applications deployed from this repository to Heroku.\n\n"
    md_list_heading = "## App List\n\n"
    apps_for_md_content.sort()
    md_app_list_str = "\n".join(apps_for_md_content) + "\n" if apps_for_md_content else ""
    final_apps_md_content = md_header + md_intro + md_list_heading + md_app_list_str

    # --- Prepare apps.json Content ---
    dynamic_json_data = {
        "apps": sorted(apps_for_json_data, key=lambda x: x.get('name', '')),
        "metadata": {
            "last_generated_run_id": current_workflow_run_id,
            "generated_at": os.environ.get("GITHUB_SHA"),
            "timestamp": os.environ.get("GITHUB_DATE") or os.environ.get("BUILD_DATE") or "",
            "workflow_name": os.environ.get("GITHUB_WORKFLOW"),
            "workflow_run_url": f"https://github.com/{os.environ.get('GITHUB_REPOSITORY')}/actions/runs/{current_workflow_run_id}"
        }
    }
    new_json_content = json.dumps(dynamic_json_data, indent=2) + "\n"

    # --- Determine if files were updated and write if allowed ---
    apps_md_updated_flag = False
    apps_json_updated_flag = False
    last_uploaded_run_id_output = "" # Will be current_workflow_run_id if uploaded

    # Check and set flag for apps.md
    current_md_content = ""
    if os.path.exists(APPS_MD_PATH):
        with open(APPS_MD_PATH, "r") as f:
            current_md_content = f.read()

    if final_apps_md_content != current_md_content:
        apps_md_updated_flag = True
        print("::notice::apps.md content has changed. 'apps_md_updated_flag' set to true.")
    else:
        print("::notice::apps.md content is unchanged. 'apps_md_updated_flag' set to false.")

    # Check and write apps.json
    if is_write_allowed(HOMEPAGE_APPS_JSON_PATH):
        current_json_content = ""
        if os.path.exists(HOMEPAGE_APPS_JSON_PATH):
            with open(HOMEPAGE_APPS_JSON_PATH, "r") as f:
                current_json_content = f.read()
        
        # Logic: Force update if flag from find_apps is true, OR if content naturally differs
        if new_json_content != current_json_content or force_upload_from_find_apps:
            os.makedirs(os.path.dirname(HOMEPAGE_APPS_JSON_PATH), exist_ok=True)
            try:
                with open(HOMEPAGE_APPS_JSON_PATH, "w") as f:
                    f.write(new_json_content)
                apps_json_updated_flag = True
                last_uploaded_run_id_output = current_workflow_run_id # Set output if uploaded
                print(f"::notice::Successfully updated {HOMEPAGE_APPS_JSON_PATH}")
                if force_upload_from_find_apps:
                    print("::notice::apps.json was updated due to force_upload_from_find_apps flag.")
            except Exception as e:
                print(f"::error::Failed to write {HOMEPAGE_APPS_JSON_PATH}: {e}", file=sys.stderr)
                sys.exit(1)
        else:
            print(f"::notice::{HOMEPAGE_APPS_JSON_PATH} content is unchanged (and no force upload). 'apps_json_updated_flag' set to false.")
    else:
        apps_json_updated_flag = False
        print(f"::warning::{HOMEPAGE_APPS_JSON_PATH} not allowed to be written. 'apps_json_updated_flag' set to false.")

    # --- Output flags and content to GITHUB_OUTPUT ---
    with open(os.environ["GITHUB_OUTPUT"], "a") as output_file:
        md_delimiter = "EOF_APPS_MD_CONTENT"
        output_file.write(f"apps_md_section_content<<{md_delimiter}\n")
        output_file.write(final_apps_md_content)
        output_file.write(f"{md_delimiter}\n")
        
        output_file.write(f"apps_md_updated_flag={str(apps_md_updated_flag).lower()}\n")
        output_file.write(f"apps_json_updated_flag={str(apps_json_updated_flag).lower()}\n")
        # Output the run ID if this job successfully updated apps.json, otherwise empty string
        output_file.write(f"last_uploaded_run_id={last_uploaded_run_id_output}\n")

if __name__ == "__main__":
    main()
