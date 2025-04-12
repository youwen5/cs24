{
  ninja,
  meson,
  stdenv,
}:
stdenv.mkDerivation {
  name = "cs24-lab02";

  src = ./.;

  nativeBuildInputs = [
    ninja
    meson
  ];
}
