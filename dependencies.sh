
#!/bin/bash

# Install necessary packages
sudo apt-get update
sudo apt-get install -y build-essential
sudo apt-get install -y libsoil-dev
sudo apt-get install -y libglew-dev
sudo apt-get install -y freeglut3-dev
sudo apt-get install -y libglu1-mesa-dev
sudo apt-get install -y libglm-dev

# Print installation success message
echo "Dependencies installed successfully!"
