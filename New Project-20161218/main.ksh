function todo(){
    b=$0
    a=$1;
    
    echo $#;
}

echo "Hello World!";


echo "$1";

todo "SALUT", "DEUX";


if [ $1 == "AAAA" ] 
then
    echo "QUADRUPLE A";
fi

awk -F":" '{print $1}' /etc/passwd;


