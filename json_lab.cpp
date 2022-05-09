#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>

struct tree
{
    std::string key = "";
    std::string first = "";
    std::string second = "";
};

std::string create_key(std::string str)
{
    std::string key = "";
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] != ':')
        {
            key = key + str[i];
        }
        else
        {
            break;
        }
    }
    return key;
}

std::string create_value(std::string str, std::string key)
{
    std::string value = "";
    for (int i = key.length() + 1; i < str.length(); i++)
    {
        value = value + str[i];
    }
    return value;
}

tree create_tree(std::string first, std::string second , std::string key)
{
    tree object;
    object.key = key;
    object.first = first;
    object.second = second;
    return object;
}

std::string input(std::string input , std::string helper){

std::cout << "Input the argument you want or you can left it empty to take the initial value which is " 
<< std::endl ;
std::cout << helper << " = " ;
std::string inputclone = input;
std::cin >> input ;
if(input == " " ){
    return inputclone;
}
else{
    return input;
}
}


std::string input_for_map (std::string value , std::string key ){

std::cout << "Input the argument you want or you can left it empty to take the initial value which is " 
<< std::endl ;
std::cout << key << " = " ;
std::string inputclone = value;
std::cin >> value ;
if(value == " " ){
    return inputclone;
}
else{
    return value;
}

}


int main()
{
    std::map<std::string, std::string> json;
    tree tree_arr[10];
    int iterator = 0;
    std::ifstream fin;
    fin.open("text.txt");
    std::ofstream myfile ("json.txt");
    std::string str = "";
    std::string object = "";
    std::string helper = "";
    std::string key = "";
    std::string value = "";
    std::string tree_value = "";
    std::string first = "";
    std::string second = "";
    bool check = true;
    while (!(fin.eof()))
    {
        getline(fin, str, ',');
        str.erase(std::remove(str.begin(), str.end(), '"'), str.end());
        str.erase(std::remove(str.begin(), str.end(), '{'), str.end());
        str.erase(std::remove(str.begin(), str.end(), '}'), str.end());
        str.erase(std::remove(str.begin(), str.end(), ';'), str.end());
        key = create_key(str);
        value = create_value(str, key);
        for (int i = 0; i < value.length(); i++)
        {
            if (value[i] == ':')
            {
                check = false;
            }
        }
        if (check == true)
        {
            value = input_for_map(value , key); 
            json.insert({key, value});
        }
        else {
            first = create_key(value);
            second = create_value(value , key);
            first = input(first , key);
            second = input(second , first);
            tree_arr[iterator] = create_tree ( first , second , key );
            iterator++;
        }
    }
        myfile << '{' ;
        for (auto itr = json.begin(); itr != json.end(); ++itr) {
        myfile << '"' << itr->first << '"' << ':' << '"'
          << itr->second << '"' << ',';
    }
        for ( int i = 0 ; i < 10 ; i++){
            if(tree_arr[i].key == ""){
                break;
            }
            else {
        myfile << '"' << tree_arr[i].key << '"' << ':' << '{' <<
        '"' << tree_arr[i].first << '"' << ':' << '"' << tree_arr[i].second << '"'
        << '}' ;
            }
    }
    myfile << '}';


}
