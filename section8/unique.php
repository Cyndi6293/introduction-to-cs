<?php
    //Check for argument
    if ( $argv[1] == NULL)
    {
        printf("Usage: php %s filename\n", $argv[0]);
        return;
    }
    
    //Open file, check if successfuly opened file
    $fhandle = fopen( $argv[1], "r" );    
    if ( $fhandle == false )
    {
        printf("Couldn't open file\n");
        return;
    }    
        
    //Read file, write uniques to Words array
    $words = [];
    while ( ( $buffer = fgets($fhandle,4096) ) != false )
    {
        $words[strtolower(chop($buffer))] = true;
        //echo $buffer;
    }
        
    //Add keys of Words array to Outarray as elements 
    $output = [];
    $i = 0;
    foreach ( $words as $key => $value)
    {
        $output[$i] = $key;
        $i++;
        //print $key."\n";
        //print "words[".$key."]=".$value."\n";
    }
    
    //Sort and print Output array
    sort($output);
    foreach($output as $word)
    {
        print $word."\n";
    }
    fclose($fhandle);
?>

