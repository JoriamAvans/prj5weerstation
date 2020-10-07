<?php
#test for given parameters
if(isset($_GET["temperature"]) && isset($_GET["humidity"])) {
	$temperature = $_GET["temperature"];
	$humidity = $_GET["humidity"];
	
	#timeSinceMeasurement is optional, will take current time if not set
	if(isset($_GET["timeSinceMeasurement"])) {
		$timeSinceUpdate = $_GET["timeSinceMeasurement"];
		$timestamp = time() - $timeSinceUpdate;
	} else {
		$timestamp = time();
	}
	http_response_code(200);
	
#if invalid-too few parameters are given± return error code 400
} else {
	http_response_code(400);
	exit("invalid request ERR_CODE(400)");
}

#parse unix timestamp to datetime
$mysqlDateTime = date("Y-m-d H:i:s", $timestamp);

$servername = "databases.aii.avans.nl";
$username = "hkuipers1";
$password = "Ab12345";
$dbname = "hkuipers1_db";

#start connection
$conn = new mysqli($servername, $username, $password, $dbname);

#Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

#give brief overview of sent values for debugging purposes
echo 'temperature: '. $temperature . "<br>";
echo 'humidity:    '. $humidity . "<br>";
echo 'time:        '. $timestamp . "<br>";

$sql = "INSERT INTO weatherStationMeasurements (humidity, temperature, timestamp)
VALUES ('" . $humidity . "', '" . $temperature . "', '" . $mysqlDateTime . "')";

#send data to sql database
if ($conn->query($sql) === TRUE) {
  echo "New record created successfully";
} else {
  http_response_code(400);
  echo "Error: " . $sql . "<br>" . $conn->error;
}

#close connection
$conn->close();
?>