{
  description = "flake for building ideal gas simulator";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = { self, nixpkgs }: 
  let
      pkgs = import nixpkgs { system = "x86_64-linux"; };
  in 
  {

    devShells.x86_64-linux = {
      default = pkgs.mkShell {
        nativeBuildInputs = with pkgs; [

          clang-tools
          glm
          gcc
          glfw
          glew

        ];
        packages = with pkgs; [
          bear
        ];
      };
    };

    packages.x86_64-linux = {

      default = pkgs.stdenv.mkDerivation {

        name = "IdealGasSimulator";

        nativeBuildInputs = with pkgs; [
          gcc
        ];

        buildInputs = with pkgs; [
          glm
          glfw
          glew
        ];

        src = ./.;
        buildPhase = ''
        mkdir -p bin
        make
        '';
        installPhase = ''
        mkdir -p $out/bin
        mv target/IdealGasSimulator $out/bin
        mv target/res $out/bin/res
        '';
      };
    };
  };
}
