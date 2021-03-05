/* script file */
let tabledata1 = document.getElementById('tabledata-feather')
let tabledata2 = document.getElementById('tabledata-nodemcu')
let tabledata3 = document.getElementById('tabledata-unidentified')

fetch("https://cosmosdb-iot20-save-get.azurewebsites.net/api/GetFromCosmosdb?code=oMXAifKJkaXdKftp7rBnvlwQTmzWWrsupNTHstcgI9qJlMJi30Y04w==")
.then(res => res.json())
.then(data =>{
    for(let row of data){
        if(row.deviceid == "feather")
            tabledata1.innerHTML += `<tr class="table-dark"><td>${row.id}</td><td>${row.deviceid}</td><td>${row.temperature}°C</td><td>${row.humidity}%</td><td>${row.formatted_time}</td>`
        else if(row.deviceid == "nodemcu")
            tabledata2.innerHTML += `<tr class="table-dark"><td>${row.id}</td><td>${row.deviceid}</td><td>${row.halleffect}</td><td>${row.formatted_time}</td>`
        else
            tabledata3.innerHTML += `Unidentified device ${row.deviceid} with # ${row.id}`
    }
})