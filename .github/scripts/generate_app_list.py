import json
import os
import sys

def main():
    # --- Retrieve Writable Files Secrets ---
    rwt_writable_files_str = os.environ.get("RWT_WRITABLE_FILES")
    allowed_write_paths = []
    if rwt_writable_files_str:
        allowed_write_paths = [os.path.normpath(p.strip()) for p in rwt_writable_files_str.split(',') if p.strip()]
    
    def is_write_allowed(target_path):
        normalized_target_path = os.path.normpath(target_path)
        for allowed_path in allowed_write_paths:
            if normalized_target_path == allowed_path:
                return True
        print(f"::warning::SECURITY ALERT: Attempted to write to '{target_path}', but it is not listed in RWT_WRITABLE_FILES secrets. Write operation skipped.", file=sys.stderr)
        print(f"::warning::Please ensure the corresponding secret (e.g., 'RWT_WRITABLE_FILE_APPS_MD' or 'RWT_WRITABLE_FILE_HOMEPAGE_APPS_JSON') is correctly set with the exact path '{target_path}' if this write is intended.", file=sys.stderr)
        return False

    # --- Data Collection Logic ---
    app_dirs_json_raw = os.environ.get("APP_DIRS_JSON_FROM_FIND_APPS") 
    app_data_matrix_json = os.environ.get("APP_DATA_MATRIX_JSON") # This is needed for herokuAppName and deployedUrl

    if not app_dirs_json_raw:
        print("::error::APP_DIRS_JSON_FROM_FIND_APPS environment variable is missing.", file=sys.stderr)
        sys.exit(1)
    if not app_data_matrix_json:
        print("::error::APP_DATA_MATRIX_JSON environment variable is missing.", file=sys.stderr)
        sys.exit(1)

    try:
        app_dirs_raw = json.loads(app_dirs_json_raw) # e.g., ["homepage-app", "homepage-app/to_do_list"]
        app_data_parsed = json.loads(app_data_matrix_json) # e.g., [{"app_dir": "homepage-app", "herokuAppName": "...", "url": "..."}, ...]
    except json.JSONDecodeError:
        print(f"::error::Failed to parse JSON from env vars. Raw dirs: {app_dirs_json_raw}, Matrix data: {app_data_matrix_json}", file=sys.stderr)
        sys.exit(1)

    # Create a dictionary for quick lookup of app data by app_dir (from matrix data)
    app_data_lookup = {item["app_dir"]: item for item in app_data_parsed}

    apps_for_md_content = [] 
    apps_for_json_data = []  

    apps_updated_flag_md = False 
    apps_updated_flag_json = False 

    for app_dir in app_dirs_raw: # Iterate over the raw list of app directories found by find_apps
        app_folder_name = os.path.basename(app_dir)
        
        # Get the full app data (including herokuAppName and deployedUrl) from the lookup dictionary
        app_info = app_data_lookup.get(app_dir)

        if not app_info:
            print(f"::warning::App data for '{app_dir}' not found in matrix data. Skipping. This might indicate a mismatch between find_apps and apps.json.", file=sys.stderr)
            continue

        app_url = app_info.get("url")
        heroku_app_name_from_pkg = app_info.get("herokuAppName") # This is now directly from matrix data

        if not app_url: 
            print(f"::warning::Skipping entry for \'{app_folder_name}\' as \'url\' is missing or empty in app data. Please check apps.json generation.", file=sys.stderr)
            continue
        
        # Prepare data for apps.md
        apps_for_md_content.append(f"* **{app_folder_name}:** [{app_url}]({app_url})")
        apps_updated_flag_md = True

        # Prepare data for apps.json - NOW INCLUDING 'app_dir'
        apps_for_json_data.append({
            "app_dir": app_dir, # <--- ADDED: The full relative path
            "name": app_folder_name, # The base folder name (e.g., homepage-app, to_do_list)
            "url": app_url,
            "herokuAppName": heroku_app_name_from_pkg
        })
        apps_updated_flag_json = True

    # --- Generate apps.md Content ---
    md_header = "# 🚀 Deployed Applications\n\n"
    md_intro = "This file lists the applications deployed from this repository to Heroku.\n\n"
    md_list_heading = "## App List\n\n"
    md_app_list_str = "\n\n".join(apps_for_md_content) + "\n\n" if apps_for_md_content else ""

    final_apps_md_content = md_header + md_intro + md_list_heading + md_app_list_str

    # --- Generate apps.json File ---
    json_output_dir = os.path.join("homepage-app", "apps")
    json_output_file_path = os.path.join(json_output_dir, "apps.json")

    if is_write_allowed(json_output_file_path):
        os.makedirs(json_output_dir, exist_ok=True)
        try:
            with open(json_output_file_path, "w") as f:
                json.dump(apps_for_json_data, f, indent=2)
            print(f"::notice::Successfully generated {json_output_file_path}")
        except Exception as e:
            print(f"::error::Failed to write {json_output_file_path}: {e}", file=sys.stderr)
            sys.exit(1)
    else:
        apps_updated_flag_json = False

    # --- Write to GITHUB_OUTPUT for apps.md ---
    md_delimiter = "EOF_APPS_MD_CONTENT"
    with open(os.environ["GITHUB_OUTPUT"], "a") as output_file:
        output_file.write(f"apps_md_section_content<<{md_delimiter}\n")
        output_file.write(final_apps_md_content)
        output_file.write(f"{md_delimiter}\n")
        output_file.write(f"apps_md_updated_flag={str(apps_updated_flag_md).lower()}\n")

    # Output a flag for the apps.json generation status
    with open(os.environ["GITHUB_OUTPUT"], "a") as output_file:
        output_file.write(f"apps_json_updated_flag={str(apps_updated_flag_json).lower()}\n")


if __name__ == "__main__":
    main()
