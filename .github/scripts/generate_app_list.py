import json
import os
import sys

def main():
    # --- Retrieve Writable Files Secrets (Individual) ---
    allowed_write_paths = []
    
    # Check for apps.md secret
    apps_md_path = os.environ.get("RWT_WRITABLE_FILE_APPS_MD")
    if apps_md_path:
        allowed_write_paths.append(os.path.normpath(apps_md_path.strip()))
    
    # Check for homepage-app/apps/apps.json secret
    homepage_apps_json_path = os.environ.get("RWT_WRITABLE_FILE_HOMEPAGE_APPS_JSON")
    if homepage_apps_json_path:
        allowed_write_paths.append(os.path.normpath(homepage_apps_json_path.strip()))

    # Function to check if a target path is allowed
    def is_write_allowed(target_path):
        normalized_target_path = os.path.normpath(target_path)
        if normalized_target_path in allowed_write_paths:
            return True
        
        # --- REFINED WARNING MESSAGE for individual secrets ---
        print(f"::warning::SECURITY ALERT: Attempted to write to '{target_path}', but it is not listed in RWT_WRITABLE_FILES secrets. Write operation skipped.", file=sys.stderr)
        print(f"::warning::Please ensure the corresponding secret (e.g., 'RWT_WRITABLE_FILE_APPS_MD' or 'RWT_WRITABLE_FILE_HOMEPAGE_APPS_JSON') is correctly set with the exact path '{target_path}' if this write is intended.", file=sys.stderr)
        # --- END REFINED WARNING MESSAGE ---
        return False

    # --- Data Collection Logic (Remains unchanged) ---
    app_dirs_json = os.environ.get("APP_DIRS_JSON_FROM_FIND_APPS") 
    
    if not app_dirs_json:
        print("::error::APP_DIRS_JSON_FROM_FIND_APPS environment variable is missing.", file=sys.stderr)
        sys.exit(1)

    try:
        app_dirs = json.loads(app_dirs_json)
    except json.JSONDecodeError:
        print(f"::error::Failed to parse JSON from env var: {app_dirs_json}", file=sys.stderr)
        sys.exit(1)

    apps_for_md_content = [] 
    apps_for_json_data = []  

    apps_updated_flag_md = False 
    apps_updated_flag_json = False 

    for app_dir in app_dirs:
        app_folder_name = os.path.basename(app_dir)
        package_json_path = os.path.join(app_dir, "package.json")
        
        if not os.path.exists(package_json_path):
            print(f"::warning::package.json not found for {app_folder_name} at {app_dir}. Skipping.", file=sys.stderr)
            continue

        try:
            with open(package_json_path, "r") as f:
                package_json_data = json.load(f)
            
            app_url = package_json_data.get("deployedUrl") 
            
            if not app_url: 
                print(f"::warning::Skipping entry for \'{app_folder_name}\' as \'deployedUrl\' is missing or empty in its package.json.", file=sys.stderr)
                continue
            
            apps_for_md_content.append(f"* **{app_folder_name}:** [{app_url}]({app_url})")
            apps_updated_flag_md = True

            apps_for_json_data.append({
                "name": app_folder_name,
                "url": app_url
            })
            apps_updated_flag_json = True

        except Exception as e:
            print(f"::error::Error processing {package_json_path}: {e}", file=sys.stderr)
            continue

    # --- Generate apps.md Content ---
    md_header = "# 🚀 Deployed Applications\n\n"
    md_intro = "This file lists the applications deployed from this repository to Heroku.\n\n"
    md_list_heading = "## App List\n\n"
    md_app_list_str = "\n\n".join(apps_for_md_content) + "\n\n" if apps_for_md_content else ""

    final_apps_md_content = md_header + md_intro + md_list_heading + md_app_list_str

    # --- Generate apps.json File ---
    json_output_dir = os.path.join("homepage-app", "apps")
    json_output_file_path = os.path.join(json_output_dir, "apps.json")

    # Only write if permission is granted via secret
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
        apps_updated_flag_json = False # Mark as not updated if write was skipped

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
