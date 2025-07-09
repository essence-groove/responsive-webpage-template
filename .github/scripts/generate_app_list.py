import json
import os
import sys

def main():
    app_dirs_json = os.environ.get("APP_DIRS_JSON_FROM_FIND_APPS") 
    
    if not app_dirs_json:
        print("::error::APP_DIRS_JSON_FROM_FIND_APPS environment variable is missing.", file=sys.stderr)
        sys.exit(1)

    try:
        app_dirs = json.loads(app_dirs_json)
    except json.JSONDecodeError:
        print(f"::error::Failed to parse JSON from env var: {app_dirs_json}", file=sys.stderr)
        sys.exit(1)

    # Building content with literal newlines (\n)
    apps_md_content = "# 🚀 Deployed Applications\n\n" # Two newlines after heading
    apps_md_content += "This file lists the applications deployed from this repository to Heroku.\n\n" # Two newlines after intro text
    apps_md_content += "## App List\n\n" # Two newlines after sub-heading
    
    apps_updated_flag = False

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
                print(f"::warning::Skipping apps.md entry for \'{app_folder_name}\' as \'deployedUrl\' is missing or empty in its package.json. Please add it.", file=sys.stderr)
                continue
            
            # Add an extra newline at the end of each list item for more spacing
            apps_md_content += f"* **{app_folder_name}:** [{app_url}]({app_url})\n\n" 
            apps_updated_flag = True

        except Exception as e:
            print(f"::error::Error processing {package_json_path}: {e}", file=sys.stderr)
            continue

    # --- FIX: Simplify the escaping for GITHUB_OUTPUT ---
    # GitHub Actions recommends replacing only specific characters,
    # and then using `echo -e` in bash to decode it.
    # The literal '%' needs to be %25. Newlines need to be %0A.
    # This is standard and should work if applied only once.
    final_escaped_content = apps_md_content.replace("%", "%25").replace("\n", "%0A").replace("\r", "%0D")
    
    with open(os.environ["GITHUB_OUTPUT"], "a") as output_file:
        output_file.write(f"apps_md_section_content={final_escaped_content}\n")
        output_file.write(f"apps_md_updated_flag={str(apps_updated_flag).lower()}\n")

if __name__ == "__main__":
    main()
