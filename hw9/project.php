<?php
//GET variables
$sortType_g=$_GET['s'];
$table_g = $_GET['t'];
//echo $sortType_g;
//echo $table_g;
//Connect to SQL server
$dbUser="cs288";
$dbPass="1234Password!";
$dbName="cs288project";
$dbServer="localhost";

$sqlCon=new mysqli($dbServer,$dbUser,$dbPass,$dbName);

if($sqlCon->connect_error){
	die("Connection Failed" . $sqlCon->connect_error);
}

$tableCommand="SHOW TABLES;";
$tblResult=$sqlCon->query($tableCommand);

if($sqlCon->error){
	echo $sqlCon->error;
	die("<br>Failed to fetch tables");
}
//echo "Sql Connection Made<br>";
//take all the tables and add them into an array
//might use for multiple time selection later otherwise use most recent

$tables=array();
echo "
	<select name=\"dropdown\" id=\"dropdown\">
	<option>Use this to select a time to view stocks</option>
	";
$i=0;
while($rRow = $tblResult->fetch_row()){
	//echo implode(",",$rRow) . "<br>";
	echo "<option value=\"?t=".$i."&s=".$sortType_g."\"> " . $rRow[0] . "</option>";
	array_push($tables,$rRow[0]);
	$i++;
}
echo "	
	</select>
	";
//end list creation
//check get Values for validity
//start with check table
$tableSelection=($i-1);
if($table_g!=null&&$table_g>=0 && $table_g<sizeof($tables))
	$tableSelection=$table_g;
//now to check sorting
//list of all colum headers
$colHeaders=["#","Stock Name", "Stock Symbol","Stock Price","Market Volume","Price Change (%)","Price Change (%)"];
//1-7 (table id) , 0-1 (ascending descending)
$sortMap_a=array(
	1=>"activeNum",
	2=>"stockName",
	3=>"stockSymbol",
	4=>"stockPrice",
	5=>"stockVolume",
	6=>"chg",
	7=>"percchg"
);

$tableCmd="SELECT * FROM ".$tables[$tableSelection];
$orderName="null";
//check bounds for type
if($sortType_g[0]>0 && $sortType_g[0]<8){
	$orderName=$sortMap_a[$sortType_g[0]];
}
//ascendOr Decend
$ascDesc="asc";
if($sortType_g[2]==1)
	$ascDesc='desc';

$orderCmd="ORDER BY ".$orderName." ".$ascDesc;
$result=$sqlCon->query($tableCmd." ".$orderCmd);  
//echo $tableCmd." ".$orderCmd;
if($sqlCon->error){
	echo $sqlCon->error;
	die("<br>Failed to fetch table: ".$tables[$tableSelection]);
}
echo "<h2>Using Data From: ".$tables[$tableSelection]." </h2>";
//Table First Colum Formating
echo "<table><tr>";

for($i=0;$i<7;$i++){
	$tblAdd="";
	if($table_g!=null)
		$tblAdd=$table_g;
	$chgascdec=($ascDesc=="desc"&&($i+1)==$sortType_g[0])?0:1;
	echo "<th>"; 
	echo "<a href=\"?t=".$table_g."&s=".($i+1).",".$chgascdec."\">";
	echo $colHeaders[$i];
	echo "</a></th>";
	
}

echo "</tr>";
//Remaining Rows of the table
while($rRow = $result->fetch_row()){
	echo "<tr><td>".implode("</td><td>",$rRow) . "</td></tr>";
	//echo $rRow[0] . "<br>";
	//array_push($tables,$rRow[0]);
}
echo "</table>";

$sqlCon->close();
?>
<script type="text/javascript">
 var urlmenu = document.getElementById( 'dropdown' );
 	urlmenu.onchange = function() {
      		window.location.href=( this.options[ this.selectedIndex ].value );
 	};
</script>
