{
  ninja,
  meson,
  stdenv,
}:
stdenv.mkDerivation {
  name = "cs24-pa01";

  src = ./.;

  nativeBuildInputs = [
    ninja
    meson
  ];
}
