{
  ninja,
  meson,
  stdenv,
}:
stdenv.mkDerivation {
  name = "cs24-labs";

  src = ./.;

  nativeBuildInputs = [
    ninja
    meson
  ];
}
