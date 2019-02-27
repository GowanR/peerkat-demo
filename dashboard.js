var ctx = document.getElementById("myChart").getContext('2d');
console.log(ctx);

var ctx = document.getElementById('myChart').getContext('2d');
var chart = new Chart(ctx, {
    // The type of chart we want to create
    type: 'line',

    // The data for our dataset
    data: {
        labels: ["", "February", "March", "April", "May", "June", "July"],
        datasets: [{
            label: "Click Data",
            backgroundColor: 'rgb(255, 99, 132)',
            borderColor: 'rgb(255, 99, 132)',
            data: [1, 2, 2, 3, 1, 2, 0],
        }]
    },

    // Configuration options go here
    options: {}
});

