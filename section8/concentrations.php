<?php
    $fhandle = fopen("concentrations.txt", "r");
    if ($fhandle == false)
    {
        echo "Couldn't open file";
    }
    $i=1;
    print '<select name="concentration">'."\n";
    print "\t<option value=\"$i\"> </option>\n";
    while ( ( $buffer = fgets($fhandle,4096) ) != false )
    {
        $i++;
        print  "\t<option value=\"$i\">".chop($buffer)."</option>\n";        
    }
    print '</select>'."\n";
?>
