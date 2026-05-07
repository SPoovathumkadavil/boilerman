{
  description = "c++ library flake for |||project_name|||";

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
            gnumake
            clang-tools
            clang
            gdb
            bear
          ];

          shellHook = ''
            echo "entering c++ library development shell for |||project_name|||..."
          '';
        };
      });
}
