### Dependencies:
    nlohmann_json: https://github.com/nlohmann/json.git
    google test: https://github.com/google/googletest
    curl: https://github.com/curl/curl           

### Run program:
    ./package-checker <barch1> <branch2>

### Example:
    ./package-checker p9 p10
        p9 - the first branch name
        p10 - the second branch name    

### Installation:
- nlohmann_json:
  - cd external/
  - rm -rf json/
  - git clone https://github.com/nlohmann/json.git
    
- gtest: 
  - Ubuntu: sudo apt-get install libgtest-dev
  - CentOs: sudo yum install gtest
  - cd /usr/src/gtest
  - sudo cmake CMakeLists.txt
  - sudo make
  - sudo cp *.a /usr/lib
  
- curl:
  - Ubuntu: sudo apt-get install libcurl4-gnutls-dev
  - CentOs: yum install libcurl4-gnutls-dev

### Build projest:
    mkdir <build-directory>
    cd <build-directory>
    cmake ..
    make

### Json output format:
`
{
    "for_arch": "string",
    "report": [
        {
            "unique_package_from_p9": [
                {
                    "name": "string",
                    "epoch": int,
                    "version": "string",
                    "release": "string",
                    "arch": "string",
                    "disttag": "string",
                    "buildtime": int,
                    "source": "string"
                }
                ,
                ...
        }
        ,
        ...
    ]
}
,
`
