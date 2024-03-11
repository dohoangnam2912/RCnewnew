#include<iostream>
#include<limits.h>
#include<math.h>
#include<vector>
#include<string>
#include<stdint.h>
#include<fstream>
#include <sstream>
#include<iomanip>
using namespace std;

string hexConverter(uint8_t byte){
    string answer;
    uint8_t first = byte / 16;
    byte %= 16;
    if(first >= 10) answer += first - 10 + 'a';
    else answer += first + '0';
    if(byte >= 10) answer += byte - 10 + 'a';
    else answer += byte + '0';
    return answer;
}

string intToBinaryConverter(uint8_t n){
    string answer;
    while(n > 0){
        char letter = (n % 2 + '0');
        answer = letter + answer;
        n /= 2;
    }
    for(int i = answer.length() ; i < 8 ; i ++) answer = '0' + answer;
    return answer;
}


void swap(uint8_t &a, uint8_t &b){
    uint8_t c = a;
    a = b;
    b = c;
}


class RC4 {
    public:
        RC4(const vector<uint8_t> &seed);
        void encryptDecrypt(vector<uint8_t> &data, bool Choice);
        int imageEncryption(int data, int *i, int *j);
        int imageToHex(string fileName);
        int hexToImage(string fileName);
    private:
        vector<uint8_t> S;
        int i = 0, j = 0;
        
};

RC4::RC4(const vector<uint8_t> &seed) {
    S.resize(256);
    for(int i = 0 ; i < 256 ; i++) {
        S[i] = i;
    }
    vector<uint8_t> T;
        for(int i = 0 ; i < 256 ; i++){
            T.push_back(seed[i % seed.size()]);
        }
    for(int i = 0 ; i < 256 ; i++){
        j = (j + S[i] + T[i]) % 256;
        swap(S[i], S[j]);
    }
    i = j = 0;
}

void RC4::encryptDecrypt(vector<uint8_t> &data, bool choice){
    for(int k = 0 ; k < data.size() ; k++){
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(S[i], S[j]);
        data[k] ^= S[(S[i] + S[j]) % 256];
    }
    if(choice == 0) {
        cout << "So your encrypted text is:";
        for(int k = 0 ; k < data.size() ; k++){
            cout << hexConverter(data[k]);
        }
    }
    else if (choice == 1) {
        cout << "So your decrypted text is:";
        for(int k = 0 ; k < data.size() ; k++){
            cout << data[k] ;
        }
    }
    else if (choice == 2) {
        cout << "So your encrypted text is:";
        for(int k = 0 ; k < data.size() ; k++){
            cout << hexConverter(data[k]);
        }
    }
    
}

int RC4::imageEncryption(int data, int *i,int *j){
    *i = (*i + 1) % 256;
    *j = (*j + S[*i]) % 256;
    swap(S[*i], S[*j]);
    data ^= S[(S[*i] + S[*j]) % 256];
    cout << "So your data is: " << data;
    return data;
}

int RC4::imageToHex(string fileName){
    // Open the JPEG file in binary mode
    ifstream jpegFile(fileName, ios::binary);

    // Check if the file was opened successfully
    if (!jpegFile.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    // Open the output hex file in binary mode
    ofstream hexFile("output.hex");
    ofstream hexFile2("output2.hex");


    // Check if the file was opened successfully
    if (!hexFile.is_open()) {
        cerr << "Error creating hex file" << endl;
        jpegFile.close();
        return 1;
    }

    if (!hexFile2.is_open()) {
        cerr << "Error creating hex file 2" << endl;
        jpegFile.close();
        return 1;
    }

    // Read the JPEG file byte by byte and write the hexadecimal representation to the output file
    char byte;
    char bytenew;
    while (jpegFile.get(byte)) {
        // cout << (int)(unsigned char)byte << endl;
        hexFile << std::setw(2) << std::setfill('0') << std::hex << (int)(unsigned char)byte << " ";
        hexFile2 << setw(2) << setfill('0') << hex << imageEncryption((int)(unsigned char)bytenew,&i, &j) << " ";
        // dataString += hexConverter((uint8_t)(unsigned char)byte);
    }
    // while (jpegFile.get(bytenew)) {
    //     // dataString += hexConverter((uint8_t)(unsigned char)byte);
    // }
    // vector<uint8_t> data;
    // for(int i = 1 ; i < dataString.length() ; i+=2) {
    //     if(dataString[i] != ' ') sum = sum * 10 + (dataString[i] - '0');
    //     else {
    //         data.push_back(uint8_t(sum));
    //         sum = 0;
    //     }
    //     uint8_t sum = 0;
    //     for(int j = 0 ; j <= 1 ; j++){
    //         int add = dataString[i-j] >= 'a' && dataString[i-j] <= 'z' ? (dataString[i-j] - 'a' + 10) : dataString[i-j] - '0';
    //         sum += add * pow(16,j);
    //         data.push_back(sum);
    //     }
    // }   
    // encryptDecrypt(data, 0);


    // Close the files
    jpegFile.close();
    hexFile.close();

    cout << "Conversion successful" << endl;

    return 0;
}

int RC4::hexToImage(string fileName){
    // Open the hex file in text mode
    ifstream hexFile("output.hex");

    // Check if the file was opened successfully
    if (!hexFile.is_open()) {
        cerr << "Error opening hex file" << endl;
        return 1;
    }

    // Open the output image file in binary mode
    ofstream imageFile("output_image.jpg", ios::binary);

    // Check if the file was opened successfully
    if (!imageFile.is_open()) {
        cerr << "Error creating image file" << endl;
        hexFile.close();
        return 1;
    }

    // Read hex values from the file and convert them back to binary
    string hexValue;
    while (hexFile >> setw(2) >> hexValue) {
        istringstream hexStream(hexValue);
        int byteValue;
        hexStream >> hex >> byteValue;
        cout << byteValue;
        char byte = static_cast<char>(byteValue);
        imageFile.put(byte);
    }

    // Close the files
    hexFile.close();
    imageFile.close();

    cout << "Conversion back to image successful" << endl;

    return 0;
}

void display(){
    cout << "Welcome to the RC4 encryption! What do you like to use our service" << endl;
    cout << "1. Encryption a text" << endl;
    cout << "2. Decryption a text" << endl;
    cout << "3. Encryption an image" << endl;
    cout << "4. Decryption an image" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your service number:" << endl;
}

int main()
{
    int selection = 2;
    do {
        display();
        cin >> selection;
        vector<uint8_t> seed;
        int seedLength;
        cout << "Enter your seed length: ";
        cin >> seedLength;
        for(int i = 0 ; i < seedLength ; i++){
            cout << i << " ";
        }
        for(int i = 0 ; i < seedLength ; i++){
            int temp;
            cout << "Enter your seed letter number " << i << ": ";
            cin >> temp;
            seed.push_back(uint8_t(temp));
        }
        RC4 rc4(seed);
        if(selection == 1){
            string dataString;
            cout << "Enter your data";
            cin.ignore();  // Add this line to clear the newline character from the buffer.
            getline(cin, dataString);
            vector<uint8_t> data;
            for(int i = 0 ; i < dataString.length() ; i++) {
                if(dataString[i] != ' ') data.push_back(uint8_t(dataString[i]));
            }
            rc4.encryptDecrypt(data, 0);
        }
        if(selection == 2){
            string dataString;
            cout << "Enter your data";
            cin.ignore();
            getline(cin, dataString);
            vector<uint8_t> data;
            for(int i = 1 ; i < dataString.length() ; i+=2) {
                // if(dataString[i] != ' ') sum = sum * 10 + (dataString[i] - '0');
                // else {
                //     data.push_back(uint8_t(sum));
                //     sum = 0;
                // }
                int sum = 0;
                for(int j = 0 ; j <= 1 ; j++){
                    int add = dataString[i-j] >= 'a' && dataString[i-j] <= 'z' ? (dataString[i-j] - 'a' + 10) : dataString[i-j] - '0';
                    sum += add * pow(16,j);
                }
                data.push_back(sum);
            }
            rc4.encryptDecrypt(data, 1);
        }
        if(selection == 3) {
            string fileName;
            cout << "Enter your file name: ";
            cin.ignore();
            getline(cin, fileName);
            int result = rc4.imageToHex(fileName);
        }
    } while(selection != 5) ;
    return 0;

}


