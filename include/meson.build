sources = 'wildcard.h'

install_headers(sources, subdir: meson.project_name())

shared = shared_library(
    meson.project_name(),
    sources: sources,
    install: true,
    version: meson.project_version(),
    include_directories: include
)

static = static_library(
    meson.project_name(),
    sources: sources,
    install: true, 
    include_directories: include
)

pkg = import('pkgconfig')

pkg.generate(
    name: meson.project_name(),
    version: meson.project_version(),
    description: 'Tiny wildcard library written in single h-file without any dependencies',
    libraries: [shared, static],
    subdirs: meson.project_name()
)