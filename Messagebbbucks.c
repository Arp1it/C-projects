#include <Windows.h>
#include <stdio.h>


int main(){

    int l = MessageBoxW(NULL, L"Do You Love ME?", L"Love", MB_YESNO | MB_ICONQUESTION);

    if(l == 6){
        MessageBoxW(NULL, L"I Love You too!", L"Love", MB_OK | MB_ICONASTERISK);

        return EXIT_SUCCESS;
    }

    else{
        MessageBoxW(NULL, L"No Worries I Love You Forever! Take Care!", L"Love", MB_OK | MB_ICONEXCLAMATION);

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}