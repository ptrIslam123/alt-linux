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
  - git clone https://github.com/nlohmann/json.git
    
- gtest: 
  - sudo apt-get install libgtest-dev
  - cd /usr/src/gtest
  - sudo cmake CMakeLists.txt
  - sudo make
  - sudo cp *.a /usr/lib
  
- curl:
  - sudo apt-get install {libcurl4-gnutls-dev/libcurl4-openssl-dev/libcurl4-nss-dev}

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