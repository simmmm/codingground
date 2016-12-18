function todo(){
    b=$0
    a=$1;
    
    echo $#;
    
    echo '$@' $@;
    
    for var in $@
    do
        echo "$var"
    done
    
    echo "echo ${@[1]}"
}

echo "Hello World!";


echo "$1";

todo "SALUT" "DEUX";


if [ $1 == "AAAA" ] 
then
    echo "QUADRUPLE A";
fi

awk -F":" '{print $1}' /etc/passwd | head -1;

LINE=`wc -l /etc/passwd | awk '{print $1}'`

echo $LINE "lignes au total dans le fichier...";

