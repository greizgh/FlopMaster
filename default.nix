with import <nixpkgs> {};
with pkgs;
stdenv.mkDerivation {
  name = "flopmaster";
  src = ./.;
  buildInputs = [ cmake boost ]
   ++ lib.optional stdenv.isLinux alsaLib;
}
