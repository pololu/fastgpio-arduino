SITEDIR=../pololu.github.io
rm -R ../docs
doxygen
rm -R $SITEDIR/fastgpio-arduino
cp -R docs/html $SITEDIR/fastgpio-arduino
