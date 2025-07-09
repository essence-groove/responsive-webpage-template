import json
import os
import sys

def main():
    # Get app directories JSON from the previous job's output via environment variable
    app_dirs_json = os.environ.get("APP_DIRS_JSON_FROM_FIND_APPS") 
    
    if not app_dirs_json:
        print("::error::APP_DIRS_JSON_FROM_FIND_APPS environment variable is missing.", file=sys.stderr)
        sys.exit(1)

    try:
        app_dirs = json.loads(app_dirs_json)
    except json.JSONDecodeError:
        print(f"::error::Failed to parse JSON from env var: {app_dirs_json}", file=sys.stderr)
        sys.exit(1)

    apps_md_content = "# 🚀 Deployed Applications\n\n"
    apps_md_content += "This file lists the applications deployed from this repository to Heroku.\n\n"
    apps_md_content += "## App List\n\n"
    apps_updated_flag = False

    # Read package.json for each app to get herokuAppName
    for app_dir in app_dirs:
        app_folder_name = os.path.basename(app_dir)
        package_json_path = os.path.join(app_dir, "package.json")
        
        if not os.path.exists(package_json_path):
            print(f"::warning::package.json not found for {app_folder_name} at {app_dir}. Skipping.", file=sys.stderr)
            continue

        try:
            with open(package_json_path, "r") as f:
                package_json_data = json.load(f)
            
            heroku_app_target_name = package_json_data.get("herokuAppName")
            
            if not heroku_app_target_name:
                print(f"::warning::Skipping apps.md entry for \'{app_folder_name}\' as \'herokuAppName\' is missing or empty in its package.json.", file=sys.stderr)
                continue
            
            app_url = f"https://{heroku_app_target_name}.herokuapp.com/"
            apps_md_content += f"* **{app_folder_name}:** [{app_url}]({app_url})\n"
            apps_updated_flag = True

        except Exception as e:
            print(f"::error::Error processing {package_json_path}: {e}", file=sys.stderr)
            continue

    # Output the generated content and a flag indicating if there's anything to write
    # Encode newlines for GITHUB_OUTPUT as it expects a single-line string
    escaped_content = apps_md_content.replace("\n", "%0A").replace("\r", "%0D").replace("%", "%25")
    
    # Write directly to $GITHUB_OUTPUT file
    # Ensure this writes to the file, not just stdout
    with open(os.environ["GITHUB_OUTPUT"], "a") as output_file:
        output_file.write(f"apps_md_section_content={escaped_content}\n")
        output_file.write(f"apps_md_updated_flag={str(apps_updated_flag).lower()}\n")

if __name__ == "__main__":
    main()
