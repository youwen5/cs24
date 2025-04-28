{
  ninja,
  meson,
  stdenv,
}:
stdenv.mkDerivation {
  name = "cs24-lab03";

  src = ./.;

  nativeBuildInputs = [
    ninja
    meson
  ];
}
