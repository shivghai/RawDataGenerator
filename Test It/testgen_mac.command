cd "$(dirname "$0")"

if [ -e "testgen" ]; then
    echo "Recompile? Enter 'y' to recompile, anything else otherwise"
    read COMPILEFLAG

    if [ "$COMPILEFLAG" = "y" ]; then
        echo "Compiling...."
        rm testgen
        g++ helperFunctions.cpp main.cpp -o testgen
        echo "Compilation successful"
    fi

    echo "Enter 'r' to open README and execute, anything else otherwise"
    read READOREXEC

    if [ "$READOREXEC" = "r" ]; then
        echo "Opening README and executing.."
        open README.txt
    else
        echo "Executing..."
    fi
    ./testgen

else
    echo "Compiling...."
    rm testgen
    g++ helperFunctions.cpp main.cpp -o testgen
    if [-e "testgen"]; then
        echo "Compilation successful. Enter 'r' to open README and execute"
        read READOREXEC

        if [ "$READOREXEC" = "r" ]; then
            echo "Opening README and executing.."
            open README.txt
        else
            echo "Executing..."
        fi
    ./testgen
    else
        echo "Compilation unsuccesful."
    fi
fi

