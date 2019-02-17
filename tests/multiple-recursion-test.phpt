--TEST--
Ensure recursion limit is always correctly applied when multiple recursions take place
--FILE--
<?php

$a = 0;
function doRecursion(){
	try{
		a();
	}catch(\Error $e){
		global $a;
		var_dump($a);
	}
}

function a(){
	global $a;
	$a++;
	a();
}
$a = 0;
doRecursion();
$a = 0;
doRecursion();

?>
--EXPECT--
int(255)
int(255)