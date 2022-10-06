### Dependencies:
    nlohmann_json: https://github.com/nlohmann/json.git
    google test: https://github.com/google/googletest
    curl: https://github.com/curl/curl           

### Run program:
    ./package-checker <barch1> <branch2> <output-file-path>

### Example:
    ./package-checker p9 p10 result.txt
        p9 - name of the first branch
        p10 - name of the second branch    
        result.txt - output file name that will contains result

### Installation:
- nlohmann_json:
  - cd external/
  - rm -rf json
  - git clone https://github.com/nlohmann/json.git
    
- gtest: 
  - Ubuntu: sudo apt-get install libgtest-dev
  - CentOs: sudo yum install gtest
  - cd /usr/src/gtest
  - sudo cmake CMakeLists.txt
  - sudo make
  - sudo cp *.a /usr/lib
  
- curl:
  - Ubuntu: sudo apt-get install curl
  - CentOs: yum install curl

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
    ]
}
`