<?php

$temperature = $_GET["temperature"];
$humidity = $_GET["humidity"];
$timeSinceUpdate = $_GET["timeSinceMeasurement"];
$timestamp = time() - $timeSinceUpdate;
$mysqlDateTime = date("Y-m-d H:i:s", $timestamp);

$servername = "localhost";
$username = "weatherStationClient";
$password = "prj5weatherStation";
$dbname = "prj5weerstation";

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
VALUES ('" . $temperature . "', '" . $humidity . "', '" . $mysqlDateTime . "')";

if ($conn->query($sql) === TRUE) {
  echo "New record created successfully";
} else {
  echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();
?>