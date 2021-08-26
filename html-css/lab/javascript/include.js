$(function () {
    $.ajax({
        type: 'GET',
        url: '../blogs/list.html',
        dataType: 'html',
        success: function (data) {
            $('#list').append(data);
        },
        error: function () {
            alert('include error!!');
        }
    });
});