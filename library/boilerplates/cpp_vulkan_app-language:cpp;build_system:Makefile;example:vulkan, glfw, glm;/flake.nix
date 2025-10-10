{
  description = "vulkan-c++ flake for |||name|||";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
      in
      {
        devShells.default = pkgs.mkShell {
          packages = with pkgs; [
            gnumake # for 'make'
            clang-tools # for clangd
            clang # or gcc
            gdb # for debugging
            bear # for compile_db

            # vulkan
            vulkan-loader
            vulkan-headers
            vulkan-tools
            vulkan-validation-layers

            # openGL shader language
            glslang

            glfw
            glm
          ];

          shellHook = ''
            echo "entering vulkan-c++ development shell for |||name|||..."
          '';
        };
      });
}
