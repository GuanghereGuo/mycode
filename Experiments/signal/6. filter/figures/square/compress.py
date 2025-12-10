import os
from PIL import Image

def compress_jpgs_in_current_dir(quality=70):
    current_dir = os.getcwd()
    output_dir = os.path.join(current_dir, "compressed")

    os.makedirs(output_dir, exist_ok=True)

    for filename in os.listdir(current_dir):
        if filename.lower().endswith(".jpg") or filename.lower().endswith(".jpeg"):
            input_path = os.path.join(current_dir, filename)
            output_path = os.path.join(output_dir, filename)

            with Image.open(input_path) as img:
                img.save(output_path, "JPEG", optimize=True, quality=quality)

            print(f"Compressed: {filename} → {output_path}")

    print("\nDone! All images saved to ./compressed/")

if __name__ == "__main__":
    compress_jpgs_in_current_dir(quality=50)
