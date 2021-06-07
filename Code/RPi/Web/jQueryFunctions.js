 $(document).ready(function(){
        console.log("Script started"); //Debugging command, ensure the script starts
        $.ajax({
            type:'POST',
            url: "CheckSettings.php",
            data: {Fetch: "All"},
            dataType: 'json',
            success: function(response){
                MultiplePumps = response['MultiplePumps'];
                MasterSchedule = response['MasterSchedule'];
            }
        })
    $("#DeviceTypeSelect").on("change", function(){ //When the dropdown menu for type of device is changed

        var selected = $(this).val() //Gets which value is selected

        if(selected == "Valve" || selected == "Tank" || selected == "Pump"){

            $("#Digital").prop("checked", true); //Checking the appropriate radio buttons for these devices
            $("#Output").prop("checked", true);
            $("#Digital").attr("disabled", true); //Disabling the radio buttons to prevent user error
            $("#Output").attr("disabled", true);

            $.ajax({ //Perform an AJAX request to find out which pins are available
                type:"POST", //Define request type
                url:"PinChecks.php", //Choose the script file
                data: {PinType: "DigitalOut"}, //Send along some data for the script
                dataType: "json", //Define the datatype for the return
                success: function(response){ //What to do if the request is successful

                    var len = response.length; //How many records?
                    console.log("test");

                        $("#sel_user").empty();

                    for(var i = 0; i < len; i++){ //For each record, extract the pin number
                        var id = response[i]['PinNum'];
                        console.log(id);


                        $("#Pins").append("<option value='"+id+"'>"+id+"</option>"); //Add the pins to the dropdown by pin number
                    }
                console.log("test2");
                },
                error: function(xhr){ //What if it fails?
                        console.log("Error: "+xhr.status+" "+xhr.statusText);
                },
                complete: function(response){ //A debug to alert that the process is done
                        console.log("Finished");
                }
            })
        } else if(selected == "FlowMeter" || selected == "Float"){
            $("#Digital").prop("checked", true);
            $("#Input").prop("checked", true);
            $("#Digital").attr("disabled", true); //Disabling the radio buttons to prevent user error
            $("#Input").attr("disabled", true);            

            $.ajax({
                type:"POST",
                url:"PinChecks.php",
                data: {PinType: "DigitalIn"}, //Send along some data for the script
                dataType: "json", //Define the datatype for the return
                success: function(response){ //What to do if the request is successful

                    var len = response.length;
                    console.log("test");

                        $("#sel_user").empty();

                    for(var i = 0; i < len; i++){
                        var id = response[i]['PinNum'];
                        console.log(id);


                        $("#Pins").append("<option value='"+id+"'>"+id+"</option>");
                    }
                console.log("test2");
                },
                error: function(xhr){ //What if it fails?
                        console.log("Error: "+xhr.status+" "+xhr.statusText);
                },
                complete: function(response){ //A debug to alert that the process is done
                        console.log("Finished");
                }
            })
        } else { //When it's a different kind of device
            $("#Digital").attr("required", true); //Require that these choices be made
            $("#Input").attr("required", true);
        }
    })
    $("#Input").on("change", function(){
        if($("#Input").prop("checked") && $("#Digital").prop("checked")){
            $.ajax({
                type:"POST",
                url:"PinChecks.php",
                data: {PinType: "DigitalIn"}, //Send along some data for the script
                dataType: "json", //Define the datatype for the return
                success: function(response){ //What to do if the request is successful

                    var len = response.length;
                    console.log("test");

                        $("#sel_user").empty();

                    for(var i = 0; i < len; i++){
                        var id = response[i]['PinNum'];
                        console.log(id);


                        $("#Pins").append("<option value='"+id+"'>"+id+"</option>");
                    }
                console.log("test2");
                },
                error: function(xhr){ //What if it fails?
                        console.log("Error: "+xhr.status+" "+xhr.statusText);
                },
                complete: function(response){ //A debug to alert that the process is done
                        console.log("Finished");
                }
            })
        } else if($("#Input").prop("checked") && $("#Analog").prop("checked")){
            $.ajax({
                type:"POST",
                url:"PinChecks.php",
                data: {PinType: "AnalogIn"}, //Send along some data for the script
                dataType: "json", //Define the datatype for the return
                success: function(response){ //What to do if the request is successful

                    var len = response.length;
                    console.log("test");

                        $("#sel_user").empty();

                    for(var i = 0; i < len; i++){
                        var id = response[i]['PinNum'];
                        console.log(id);


                        $("#Pins").append("<option value='"+id+"'>"+id+"</option>");
                    }
                console.log("test2");
                },
                error: function(xhr){ //What if it fails?
                        console.log("Error: "+xhr.status+" "+xhr.statusText);
                },
                complete: function(response){ //A debug to alert that the process is done
                        console.log("Finished");
                }
            })
        } else if($("#Output").prop("checked") && $("#Digital").prop("checked")){
            $.ajax({
                type:"POST",
                url:"PinChecks.php",
                data: {PinType: "DigitalOut"}, //Send along some data for the script
                dataType: "json", //Define the datatype for the return
                success: function(response){ //What to do if the request is successful

                    var len = response.length;
                    console.log("test");

                        $("#sel_user").empty();

                    for(var i = 0; i < len; i++){
                        var id = response[i]['PinNum'];
                        console.log(id);


                        $("#Pins").append("<option value='"+id+"'>"+id+"</option>");
                    }
                console.log("test2");
                },
                error: function(xhr){ //What if it fails?
                        console.log("Error: "+xhr.status+" "+xhr.statusText);
                },
                complete: function(response){ //A debug to alert that the process is done
                        console.log("Finished");
                }
            })
        } else {
            $.ajax({
                type:"POST",
                url:"PinChecks.php",
                data: {PinType: "DigitalIn"}, //Send along some data for the script
                dataType: "json", //Define the datatype for the return
                success: function(response){ //What to do if the request is successful

                    var len = response.length;
                    console.log("test");

                        $("#sel_user").empty();

                    for(var i = 0; i < len; i++){
                        var id = response[i]['PinNum'];
                        console.log(id);


                        $("#Pins").append("<option value='"+id+"'>"+id+"</option>");
                    }
                console.log("test2");
                },
                error: function(xhr){ //What if it fails?
                        console.log("Error: "+xhr.status+" "+xhr.statusText);
                },
                complete: function(response){ //A debug to alert that the process is done
                        console.log("Finished");
                }
            })
        }

    })
    $("#submit").on("click", function(){
        var DevName = $("#DevName").val();
        var DevType = $("#DeviceTypeSelect").val();
        var AD = $("input:radio[name='AD']:checked").val();
        var InOut = $("input:radio[name='InOut']:checked").val();
        var Pin = $("#Pins").val();
        var Stat = $("input:radio[name='Status']:checked").val();
        $.ajax({
            type: "POST",
            url: "NewDevice.php",
            data: {DevName: DevName, DevType: DevType, AD: AD, InOut: InOut, Pin: Pin, Stat: Stat},
            dataType: 'json',
            success: function(response){
                var resp = response['Status'];
                if(resp == 1){
                    $("#SuccessMessage").prop("visibility", "visible");
                }
            }
        })
    })

    $(".PumpSwitch").on("click", function(){
        var SwitchedID = $(this).attr("id");
        console.log(Switched);

        if($("#"+SwitchedID).prop("checked")){
            if(MultiplePumps == 0){
                $(".PumpSwitch:not(#"+SwitchedID+")").prop("checked", false);
            }

            $.ajax({
                type:'POST',
                url: 'SerialCommands.php',
                data: {Pin: SwitchedID, Command: "PumpEn"},
                dataType: 'json',
                success: function(response){
                    var resp = response['Status'];
                    if(resp == 1){
                        $("#SuccessMessage").prop("visibility", "visible");
                    }
                }
            })
        }

    })


}); 


