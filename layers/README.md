# Pre-built device simulation layers files
This folder contains the pre-built Windows x64 dll for the [LunarG device simulation layer](https://github.com/LunarG/VulkanTools/tree/master/layersvt) along with the json definition file.

In order to get the example running these need to be found by the loader by doing one of the following:
- Add the layer json definition to the registry by running ```register_layer.bat``` (**Needs to be run as administrator**)
- Put both files in the bin directory of your current VulkanSDK installation
- If you have manually set your validation layer folder (by setting the ```VK_LAYER_PATH``` environment variable), put both files there
