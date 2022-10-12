### Dependencies:
    nlohmann_json: https://github.com/nlohmann/json.git
    google test: https://github.com/google/googletest
    curl: https://github.com/curl/curl           

### Run program:
    ./package-checker <barch1> <branch2> <output-file-path>

### Example:
    ./package-checker p9 p10 result.txt
        p9 - the first branch name
        p10 - the second branch name    
        result.txt - output file name that will contain the result

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
    "branch_pair": "string:string",
    "arch": "string",
    "packages": [
        {
            "name": "string", "version": "string",
            "name": "string", "version": "string",
             ...
        }
    ],
    ... 
}
`