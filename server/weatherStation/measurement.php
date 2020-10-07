<?php
if(isset($_GET["temperature"]) && isset($_GET["humidity"])) {
	$temperature = $_GET["temperature"];
	$humidity = $_GET["humidity"];
	
	if(isset($_GET["timeSinceMeasurement"])) {
		$timeSinceUpdate = $_GET["timeSinceMeasurement"];
		$timestamp = time() - $timeSinceUpdate;
	} else {
		$timestamp = time();
	}
	http_response_code(200);
	
} else {
	http_response_code(400);
	exit("invalid request ERR_CODE(400)");
}

$mysqlDateTime = date("Y-m-d H:i:s", $timestamp);

$servername = "databases.aii.avans.nl";
$username = "hkuipers1";
$password = "Ab12345";
$dbname = "hkuipers1_db";

//start connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

echo 'temperature: '. $temperature . "<br>";
echo 'humidity:    '. $humidity . "<br>";
echo 'time:        '. $timestamp . "<br>";

$sql = "INSERT INTO weatherStationMeasurements (humidity, temperature, timestamp)
VALUES ('" . $humidity . "', '" . $temperature . "', '" . $mysqlDateTime . "')";

if ($conn->query($sql) === TRUE) {
  echo "New record created successfully";
} else {
  echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();
?>