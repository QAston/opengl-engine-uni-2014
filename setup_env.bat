call vcpkg\bootstrap-vcpkg.bat
set VCPKG_DEFAULT_TRIPLET=x64-windows
set VCPKG_FEATURE_FLAGS=versions,manifests
set VCPKG_OVERLAY_PORTS=port_overlays

vcpkg\vcpkg --overlay-ports=port_overlays install