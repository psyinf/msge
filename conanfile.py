from conans import ConanFile
from conan.tools.cmake import CMake

class MSGE(ConanFile):
    name = "MSGE"
    version = "0.1"
    settings = "os", "compiler", "build_type", "arch"
    requires = [("psyinf-gmtl/0.7.1")
	            ,("yaml-cpp/0.7.0")
                ,("magic_enum/0.8.1")
                ,("glog/0.6.0")
                ,("gtest/1.12.1")      
                ]
    generators = "cmake_find_package_multi"
    
    def configure(self):
        self.options['openscenegraph'].shared = True
        self.options['openscenegraph'].with_gdal = False
        self.options['glog'].shared = True
        self.options['qt'].shared = True
        self.options['qt'].multiconfiguration = False
        
    def imports(self):    
        self.copy("*.dll", "bin", "bin")
        