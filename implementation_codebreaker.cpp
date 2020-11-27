#include <bits/stdc++.h>
using namespace std;
void printState(string s)
{
    for (auto it = s.end() - 1; it >= s.begin(); it--)
        cout << (*it);
    cout << endl;
}
string convertHexToBin(string a)
{
    string b;
    long int i = 0, size = a.size();
    while (i < size)
    {
        switch (a[i])
        {
        case '0':
            b += "0000";
            break;
        case '1':
            b += "0001";
            break;
        case '2':
            b += "0010";
            break;
        case '3':
            b += "0011";
            break;
        case '4':
            b += "0100";
            break;
        case '5':
            b += "0101";
            break;
        case '6':
            b += "0110";
            break;
        case '7':
            b += "0111";
            break;
        case '8':
            b += "1000";
            break;
        case '9':
            b += "1001";
            break;
        case 'A':
        case 'a':
            b += "1010";
            break;
        case 'B':
        case 'b':
            b += "1011";
            break;
        case 'C':
        case 'c':
            b += "1100";
            break;
        case 'D':
        case 'd':
            b += "1101";
            break;
        case 'E':
        case 'e':
            b += "1110";
            break;
        case 'F':
        case 'f':
            b += "1111";
            break;
        }
        i++;
    }
    return b;
}

void createMap(unordered_map<string, char> *um)
{
    (*um)["0000"] = '0';
    (*um)["0001"] = '1';
    (*um)["0010"] = '2';
    (*um)["0011"] = '3';
    (*um)["0100"] = '4';
    (*um)["0101"] = '5';
    (*um)["0110"] = '6';
    (*um)["0111"] = '7';
    (*um)["1000"] = '8';
    (*um)["1001"] = '9';
    (*um)["1010"] = 'A';
    (*um)["1011"] = 'B';
    (*um)["1100"] = 'C';
    (*um)["1101"] = 'D';
    (*um)["1110"] = 'E';
    (*um)["1111"] = 'F';
}

// function to find hexadecimal
// equivalent of binary
string convertBinToHex(string bin)
{
    int l = bin.size();
    int t = bin.find_first_of('.');

    // length of string before '.'
    int len_left = t != -1 ? t : l;

    // add min 0's in the beginning to make
    // left substring length divisible by 4
    for (int i = 1; i <= (4 - len_left % 4) % 4; i++)
        bin = '0' + bin;

    // if decimal point exists
    if (t != -1)
    {
        // length of string after '.'
        int len_right = l - len_left - 1;

        // add min 0's in the end to make right
        // substring length divisible by 4
        for (int i = 1; i <= (4 - len_right % 4) % 4; i++)
            bin = bin + '0';
    }

    // create map between binary and its
    // equivalent hex code
    unordered_map<string, char> bin_hex_map;
    createMap(&bin_hex_map);

    int i = 0;
    string hex = "";

    while (1)
    {
        // one by one extract from left, substring
        // of size 4 and add its hex code
        hex += bin_hex_map[bin.substr(i, 4)];
        i += 4;
        if (i == bin.size())
            break;

        // if '.' is encountered add it
        // to result
        if (bin.at(i) == '.')
        {
            hex += '.';
            i++;
        }
    }

    // required hexadecimal number
    return hex;
}
string linearDiffusion(string s)
{
    int b = s.size(), i = 0;
    /*cout << s << endl;
    reverse(s.begin(), s.end());
    cout << "s = " << s << endl;*/
    string s1;
    for (i = 0; i < b; i++)
    {
        s1 += "0";
    }

    for (i = 0; i < b - 1; i++)
    {
        s1[(3 * i) % (b - 1)] = s[i];
    }
    s1[b - 1] = s[b - 1];
    return s1;
}
string do_xor(string s1, string s2)
{
    string s;
    for (int i = 0; i < 48; i++)
    {
        s += to_string((s1[i] - '0') ^ (s2[i] - '0'));
    }
    return s;
}

string do_RC_xor(string s, vector<int> rc)
{
    int i, n = s.size() - 1;
    for (i = 0; i < 6; i++)
    {
        s[n - i] = s[n - i] ^ rc[i];
    }
    return s;
}

string s_box(string s)
{
    int i = 0, n = s.size() / 3;
    string s1;
    while (i < n)
    {
        string s2 = s.substr(3 * i, 3);
        //cout << s2 << " ";
        if (s2 == "000")
            s1 += "000";
        if (s2 == "001")
            s1 += "001";
        if (s2 == "010")
            s1 += "011";
        if (s2 == "011")
            s1 += "110";
        if (s2 == "100")
            s1 += "111";
        if (s2 == "101")
            s1 += "100";
        if (s2 == "110")
            s1 += "101";
        if (s2 == "111")
            s1 += "010";

        i++;
    }
    return s1;
}
string do_permkey(string s, string permkey)
{
    int i = 0, n = s.size() / 3;
    string s1;
    while (i < n)
    {
        string s2 = permkey.substr(2 * i, 2);
        string sub = s.substr(3 * i, 3);
        //cout << s2 << " ";
        if (s2 == "00")
            s1 += sub;
        if (s2 == "01")
        {
            s1 += sub[1];
            s1 += sub[0];
            s1 += sub[2];
        }

        if (s2 == "10")
        {
            s1 += sub[0];
            s1 += sub[2];
            s1 += sub[1];
        }

        if (s2 == "11")
        {
            s1 += sub[2];
            s1 += sub[1];
            s1 += sub[0];
        }
        i++;
    }
    return s1;
}
string oneRoundOfPRINTcipher(string plaintext, string key, string permkey, vector<int> rc, int round)
{
    string plaintextInBinary = convertHexToBin(plaintext);
    string keyInBinary = convertHexToBin(key);
    string permkeyInBin = convertHexToBin(permkey);
    string plaintext_key_xor = do_xor(plaintextInBinary, keyInBinary);
    string keyAddition = convertBinToHex(plaintext_key_xor);
    //cout << "KeyAddition = ";
    //printState(keyAddition);
    reverse(keyAddition.begin(), keyAddition.end());
    string keyAdditionInBin = convertHexToBin(keyAddition);
    string plaintext_linear_diffusion = linearDiffusion(keyAdditionInBin);
    string pLayer = convertBinToHex(plaintext_linear_diffusion);
    //cout << "pLayer = " << pLayer << endl;
    string RC_xor = do_RC_xor(plaintext_linear_diffusion, rc);
    string RC_xor_hex = convertBinToHex(RC_xor);
    //cout << "RC Xor = " << RC_xor_hex << endl;
    string keyedPermutation = do_permkey(RC_xor, permkeyInBin);
    string sboxPerm = convertBinToHex(keyedPermutation);
    //cout << "sbox perm = " << sboxPerm << endl;
    string sbox = s_box(keyedPermutation);
    string ciphertext = convertBinToHex(sbox);
    cout << "ciphertext after round" << round << " = " << ciphertext << endl;
    return ciphertext;
}
vector<vector<int>> computeRoundCounter(vector<vector<int>> RC)
{
    int i, j, k;
    vector<int> x;
    for (i = 0; i < 6; i++)
    {
        x.push_back(0);
    }
    for (i = 0; i < 48; i++)
    {
        int t = x[5] ^ x[4] ^ 1;
        for (j = 5; j >= 1; j--)
        {
            x[j] = x[j - 1];
        }
        x[0] = t;
        RC.push_back(x);
    }
    return RC;
}

int main()
{
    string plaintext = "4C847555C35B";
    string key = "C28895BA327B";
    string permkey = "69D2CDB6";
    reverse(key.begin(), key.end());
    reverse(plaintext.begin(), plaintext.end());
    cout << "Plaintext = ";
    printState(plaintext);
    vector<vector<int>> RC;
    RC = computeRoundCounter(RC);
    /*for (int i = 0; i < 48; i++)
    {
        for (auto it = RC[i].begin(); it != RC[i].end(); it++)
            cout << (*it);
        cout << endl;
    }*/
    for (int i = 0; i < 48; i++)
    {
        plaintext = oneRoundOfPRINTcipher(plaintext, key, permkey, RC[i], i + 1);
        reverse(plaintext.begin(), plaintext.end());
    }
}