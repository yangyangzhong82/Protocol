set_project("Protocol")
set_version("0.1.0")
set_languages("c++23")

add_rules("mode.debug", "mode.release")

option("shared")
    set_default(true)
    set_showmenu(true)
    set_description("Build Protocol as a shared library")
option_end()

if is_plat("windows") then
    add_defines("UNICODE", "NOMINMAX")
end

add_requires("openssl")

package("reflection")
    set_kind("library", {headeronly = true})
    set_homepage("https://github.com/SculkCatalystMC/Reflection")
    set_description("C++ reflection and JSON serialization utilities")
    add_urls("https://github.com/SculkCatalystMC/Reflection.git")
    add_versions("v1.4.0", "v1.4.0")

    on_install(function (package)
        local installdir = package:installdir("include")
        os.cp("include/sculk", installdir)

        local depsdir = path.join(package:cachedir(), "reflection-deps")
        os.mkdir(depsdir)

        local function clone_and_copy(name, url, tag, include_glob)
            local depdir = path.join(depsdir, name)
            if os.isdir(depdir) then
                os.rm(depdir)
            end
            os.vrunv("git", {"clone", "--depth", "1", "--branch", tag, url, depdir})
            os.cp(path.join(depdir, include_glob), installdir)
        end

        clone_and_copy("jsonc", "https://github.com/SculkCatalystMC/JSONC.git", "v1.4.0", "include/sculk")
        clone_and_copy("boost_pfr", "https://github.com/boostorg/pfr.git", "2.2.0", "include/boost")
        clone_and_copy("magic_enum", "https://github.com/Neargye/magic_enum.git", "v0.9.7", "include/magic_enum")
    end)

package_end()

add_requires("reflection v1.4.0")

target("Protocol")
    set_kind(get_config("shared") and "shared" or "static")

    add_headerfiles("include/(sculk/**.hpp)")
    add_files("src/**.cpp")
    add_includedirs("include", {public = true})
    add_packages("openssl", "reflection", {public = true})

    if is_plat("windows") then
        if get_config("shared") then
            add_rules("utils.symbols.export_all", {export_classes = true})
        end
        add_cxflags("/utf-8", "/W4")
        if is_mode("release") then
            add_cxflags("/O2")
        end
    else
        add_cxflags("-Wall", "-Wextra", "-Wpedantic")
        if is_mode("release") then
            add_cxflags("-O3")
        end
    end
