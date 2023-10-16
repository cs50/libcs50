{ stdenv, fetchgit }:

stdenv.mkDerivation rec {
  pname = "libcs50";
  version = "dev";

  src = fetchgit {
    url = "https://github.com/cs50/libcs50";
  };

  installPhase = ''
    mkdir -p $out/include
    cp src/cs50.h $out/include
    mkdir -p $out/lib
    cp src/cs50.c $out/lib
  '';

  meta = with stdenv.lib; {
    description = "CS50 Library for C";
    homepage = https://github.com/cs50/libcs50;
    maintainers = [ "CS50" ];
  };
}
