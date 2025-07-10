import json
import os
import sys

def main():
    # --- Retrieve Writable Files Secrets (Individual) ---
    # These secrets control if the script is allowed to write to these specific paths.
    apps_md_secret_path = os.environ.get("RWT_WRITABLE_FILE_APPS_MD")
    homepage_apps_json_secret_path = os.environ.get("RWT_WRITABLE_FILE_HOMEPAGE_APPS_JSON")

    # Normalize paths for comparison
    allowed_write_paths = set()
    if apps_md_secret_path:
        allowed_write_paths.add(os.path.normpath(apps_md_secret_path.strip()))
    if homepage_apps_json_secret_path:
        allowed_write_paths.add(os.path.normpath(homepage_apps_json_secret_path.strip()))

    def is_write_allowed(target_path):
        normalized_target_path = os.path.normpath(target_path)
        if normalized_target_path in allowed_write_paths:
            return True
        
        print(f"::warning::SECURITY ALERT: Attempted to write to '{target_path}', but it is not listed in allowed secrets (RWT_WRITABLE_FILE_APPS_MD, RWT_WRITABLE_FILE_HOMEPAGE_APPS_JSON). Write operation skipped.", file=sys.stderr)
        return False

    # --- Data Collection Logic ---
    app_data_from_find_apps_json = os.environ.get("APP_DATA_FROM_FIND_APPS")
    
    if not app_data_from_find_apps_json:
        print("::error::APP_DATA_FROM_FIND_APPS environment variable is missing. It should be provided by the 'find_apps' job.", file=sys.stderr)
        sys.exit(1)

    try:
        # app_details_list now directly contains the detailed app info from find_apps
        app_details_list = json.loads(app_data_from_find_apps_json)
    except json.JSONDecodeError:
        print(f"::error::Failed to parse JSON from APP_DATA_FROM_FIND_APPS: {app_data_from_find_apps_json}", file=sys.stderr)
        sys.exit(1)

    apps_for_md_content = [] # List to build markdown lines
    apps_for_json_data = []  # List to hold dictionaries for JSON output

    # Iterate over the app details provided by the 'find_apps' job
    for app_info in app_details_list:
        app_name = app_info.get("name")
        heroku_app_name = app_info.get("herokuAppName")
        app_url = app_info.get("url")

        if not app_name or not app_url or not heroku_app_name:
            print(f"::warning::Skipping entry due to missing data in app_info: {app_info}. Ensure all required fields (name, url, herokuAppName) are present.", file=sys.stderr)
            continue
        
        # Add to markdown content list
        apps_for_md_content.append(f"* **{app_name}:** [{heroku_app_name}]({app_url})")

        # Add to JSON data list (use the raw app_info as it already has the desired structure)
        apps_for_json_data.append(app_info)

    # --- Generate apps.md Content ---
    md_header = "# 🚀 Deployed Applications\n\n"
    md_intro = "This file lists the applications deployed from this repository to Heroku.\n\n"
    md_list_heading = "## App List\n\n"
    # Sort for consistent output
    apps_for_md_content.sort()
    md_app_list_str = "\n".join(apps_for_md_content) + "\n" if apps_for_md_content else ""

    final_apps_md_content = md_header + md_intro + md_list_heading + md_app_list_str

    # --- Generate apps.json File ---
    json_output_dir = os.path.join("homepage-app", "apps")
    json_output_file_path = os.path.join(json_output_dir, "apps.json")
    
    # Sort for consistent output
    apps_for_json_data_sorted = sorted(apps_for_json_data, key=lambda x: x.get('name', ''))
    new_json_content = json.dumps(apps_for_json_data_sorted, indent=2) + "\n" # Add newline for consistency

    # --- Determine if files were updated and write if allowed ---
    apps_md_updated_flag = False
    apps_json_updated_flag = False

    # Check and write apps.md (will be written by the subsequent workflow step)
    current_md_content = ""
    if os.path.exists("apps.md"):
        with open("apps.md", "r") as f:
            current_md_content = f.read()

    if final_apps_md_content != current_md_content:
        # We don't write it here, the workflow step does. Just set the flag.
        apps_md_updated_flag = True
        print("::notice::apps.md content has changed. 'apps_md_updated_flag' set to true.")
    else:
        print("::notice::apps.md content is unchanged. 'apps_md_updated_flag' set to false.")

    # Check and write apps.json
    if is_write_allowed(json_output_file_path):
        current_json_content = ""
        if os.path.exists(json_output_file_path):
            with open(json_output_file_path, "r") as f:
                current_json_content = f.read()
        
        if new_json_content != current_json_content:
            os.makedirs(json_output_dir, exist_ok=True)
            try:
                with open(json_output_file_path, "w") as f:
                    f.write(new_json_content)
                apps_json_updated_flag = True
                print(f"::notice::Successfully updated {json_output_file_path}")
            except Exception as e:
                print(f"::error::Failed to write {json_output_file_path}: {e}", file=sys.stderr)
                sys.exit(1)
        else:
            print(f"::notice::{json_output_file_path} content is unchanged. 'apps_json_updated_flag' set to false.")
    else:
        # If write not allowed by secret, flag it as not updated for the commit step
        apps_json_updated_flag = False
        print(f"::warning::{json_output_file_path} not allowed to be written. 'apps_json_updated_flag' set to false.")


    # --- Output flags and content to GITHUB_OUTPUT ---
    with open(os.environ["GITHUB_OUTPUT"], "a") as output_file:
        # Output the actual markdown content for the workflow step to write
        md_delimiter = "EOF_APPS_MD_CONTENT"
        output_file.write(f"apps_md_section_content<<{md_delimiter}\n")
        output_file.write(final_apps_md_content)
        output_file.write(f"{md_delimiter}\n")
        
        # Output flags for commit step condition
        output_file.write(f"apps_md_updated_flag={str(apps_md_updated_flag).lower()}\n")
        output_file.write(f"apps_json_updated_flag={str(apps_json_updated_flag).lower()}\n")


if __name__ == "__main__":
    main()
