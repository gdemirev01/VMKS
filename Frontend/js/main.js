$(document).ready(function() { 
    var profiles;
    $.get( 
        "http://192.168.1.6:8000/profiles/", { 
        }, 
        function(data) {
            $.each(data, function (i, profile) {
                var profile = (
                    '<tr>'
      
                        + '<td>' + '<input type="radio" name="current_profile" value="'  + profile.id + '"></input>'
                        + '<td>' + profile.name + '</td>'
                        + '<td>' + profile.color + '</td>'
                        + '<td>' + profile.speed + '</td>'
                        + '<td>' + profile.brightness + '</td>'
                        + '<td>' + profile.timeout + '</td>'
                        + '<td>'
                            + '<a title="edit this user" class="btn btn-default btn-sm "> <iclass="glyphicon glyphicon-edit text-primary"></i> </a>'
                            + '<a id="' + profile.id + '" class="btn btn-default btn-sm delete-profile"> <i class="glyphicon glyphicon-trash text-danger"></i> </a>'
                        + '</td>'
                    + '</tr>'
                );
                $("#form-list-profile-body").append(profile)
            });
            profiles = data;
        }
    ); 

    $("#submit").click(function(){
        var radioValue = $("input[name='current_profile']:checked").val();
        if(radioValue){
            var profile = {"current_profile": profiles[parseInt(radioValue)]["id"]}
            $.ajax({
                url: 'http://192.168.1.6:8000/profiles/current_profile/update/',
                type: 'PUT',
                data: profile,
            });
        }
    });

    $("#btn-save").click(function(){
        var name = $("input[name='profile-name']").val();
        var color = $("input[name='profile-color']").val();
        var speed = $("input[name='profile-speed']").val();
        var brightness = $("#profile-brightness-select").children("option:selected").val();
        var timeout = $("input[name='profile-timeout']").val();
        
        var profile = {
            "name": name,
            "color": color,
            "speed": speed,
            "brightness": brightness,
            "timeout": timeout,
        }
        alert(JSON.stringify(profile));

        $.ajax({
            url: 'http://192.168.1.6:8000/profiles/',
            type: 'POST',
            data: profile,
        });
    });
});