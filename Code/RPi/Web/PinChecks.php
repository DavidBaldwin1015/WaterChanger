<?php
include('config.php');
$PinType = $_POST['PinType'];

$con = mysqli_connect($host, $username, $password, $database);

if(mysqli_connect_errno()){
        echo "Failed to connect to MySQL: " . mysqli_connect_error();
}

header('Content-Type:application/json');
if($PinType == "DigitalOut"){
        $result = mysqli_query($con, "SELECT PinNum FROM Pins WHERE Pintype LIKE 'D' AND Used LIKE 0 AND PinDir LIKE 'O'");
        if(mysqli_num_rows($result) > 0){
        while($row = mysqli_fetch_assoc($result)){
                $Pin = $row['PinNum'];
                $PinArray[] = array("PinNum" => $Pin);
                }
        } else {
                echo json_encode("0");
        }
        echo json_encode($PinArray);
} else if($PinType == "DigitalIn"){
        $result = mysqli_query($con, "SELECT PinNum FROM Pins WHERE Pintype LIKE 'D' AND Used LIKE 0 AND PinDir LIKE 'I'");
        if(mysqli_num_rows($result) > 0){
        while($row = mysqli_fetch_assoc($result)){
                $Pin = $row['PinNum'];
                $PinArray[] = array("PinNum" => $Pin);
                }
        } else {
                echo json_encode("0");
        }
        echo json_encode($PinArray);
} else if($PinType == "AnalogOut"){
        $result = mysqli_query($con, "SELECT PinNum FROM Pins WHERE Pintype LIKE 'A' AND Used LIKE 0 AND PinDir LIKE 'O'");
        if(mysqli_num_rows($result) > 0){
        while($row = mysqli_fetch_assoc($result)){
                $Pin = $row['PinNum'];
                $PinArray[] = array("PinNum" => $Pin);
                }
        } else {
                echo json_encode("0");
        }
        echo json_encode($PinArray);
} else if($PinType == "AnalogIn"){
        $result = mysqli_query($con, "SELECT PinNum FROM Pins WHERE Pintype LIKE 'A' AND Used LIKE 0 AND PinDir LIKE 'I'");
        if(mysqli_num_rows($result) > 0){
        while($row = mysqli_fetch_assoc($result)){
                $Pin = $row['PinNum'];
                $PinArray[] = array("PinNum" => $Pin);
                }
        } else {
                echo json_encode("0");
        }
        echo json_encode($PinArray);
} else {
        echo json_encode("Error 2");
}
$con->close();
?> 