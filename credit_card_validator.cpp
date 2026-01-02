/* Luhn Algorithm
1) Double every second digit from right to left
2) Add all single digits from step 1
3) Add all odd numbered digits from right to left 
4) sum result from steps 2 and 3 
5) If step 4 is divisible by 10, # is valid
*/

#include <iostream>
int getdigit(const int number);
int sumodddigits(const std::string cardnumber);
int sumevendigits(const std::string cardnumber);

int main() {

    int result = 0;
    std::string cardnumber;

    std::cout << "Enter a credit card number " << '\n';
    std::getline(std::cin,cardnumber);
    result = sumevendigits(cardnumber)+sumodddigits(cardnumber);
    if(result%10==0){
        std::cout << "Credit Card is Valid" << '\n';
    }
    else{
        std::cout << "Credit Card is Invalid " << '\n';
    }
    return 0;
}

int getdigit(const int number){
    return  number %10 + (number/10%10);
}
int sumodddigits(const std::string cardnumber){
    int sum = 0;

    for(int i = cardnumber.size()-1;i>=0; i--){
        sum+= getdigit((cardnumber[i]-'0')*2);
        
    }
    return sum ;
}
int sumevendigits(const std::string cardnumber){
    int sum = 0;

    for(int i = cardnumber.size()-2;i>=0; i-=2){
        sum+= getdigit((cardnumber[i]-'0')*2);
        
    }
    return sum ;
}