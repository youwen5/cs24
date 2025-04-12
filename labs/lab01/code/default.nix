{
  ninja,
  meson,
  stdenv,
}:
stdenv.mkDerivation {
  name = "cs24-lab01";

  src = ./.;

  nativeBuildInputs = [
    ninja
    meson
  ];
}
