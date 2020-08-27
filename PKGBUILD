pkgname=fingerboard
pkgver=0.1.0
pkgrel=1
pkgdesc=''
arch=(x86_64)
url=""
depends=(qt5-base qt5-declarative qt5-quickcontrols qt5-quickcontrols2)
makedepends=(git cmake extra-cmake-modules)
provides=(fingerboard)
conflicts=(fingerboard)
sha256sums=('SKIP')

build() {
  mkdir -p "${startdir}/pkgbuild-${pkgname}-${pkgver}"

  cd "${startdir}/pkgbuild-${pkgname}-${pkgver}"
  cp -r "${startdir}/src" "${startdir}/CMakeLists.txt" ./
  
  cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/usr \
    .

  make -j$(nproc)
}
 
package() {
  (
    cd "${startdir}/pkgbuild-${pkgname}-${pkgver}"
    make -j$(nproc) DESTDIR="$pkgdir" install
  )

  echo "rm ${startdir}/pkgbuild-${pkgname}-${pkgver}"
}
