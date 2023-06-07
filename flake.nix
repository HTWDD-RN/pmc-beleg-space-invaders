{
  description = "A very basic flake";

  outputs = { self, nixpkgs }: {

    formatter.x86_64-linux = nixpkgs.legacyPackages.x86_64-linux.nixpkgs-fmt;
    devShells = {
      x86_64-linux = {
        pio = nixpkgs.legacyPackages.x86_64-linux.mkShell {
          packages = with nixpkgs.legacyPackages.x86_64-linux; [
            platformio
            llvm
            clang
            gcc
            gdb
            gef
            lldb
          ];
        };
        gui = nixpkgs.legacyPackages.x86_64-linux.mkShell {
          packages =
            with nixpkgs.legacyPackages.x86_64-linux; [
              platformio
              fritzing
              kicad
              arduino
            ];
        };
      };
    };

  };
}
