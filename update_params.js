var params_json = require('./params.json');
var fs = require('fs');


/*
** clone
*/
function clone(obj) {
    // Handle the 3 simple types, and null or undefined
    if (null == obj || "object" != typeof obj) return obj;

    // Handle Date
    if (obj instanceof Date) {
        var copy = new Date();
        copy.setTime(obj.getTime());
        return copy;
    }

    // Handle Array
    if (obj instanceof Array) {
        var copy = [];
        for (var i = 0, len = obj.length; i < len; i++) {
            copy[i] = clone(obj[i]);
        }
        return copy;
    }

    // Handle Object
    if (obj instanceof Object) {
        var copy = {};
        for (var attr in obj) {
            if (obj.hasOwnProperty(attr)) copy[attr] = clone(obj[attr]);
        }
        return copy;
    }

    throw new Error("Unable to copy obj! Its type isn't supported.");
}

/*
**
**  get source
**
*/
var source_body;
fs.readFile( './source.json', 'utf8', function( err, data ){

    if( err ){
        console.log( err );
    }

    source_body = data;


    /*
    **
    **  save old params
    **
    */
    fs.writeFile( './params.json.backup', JSON.stringify( clone( params_json ) ), function( err ){

        if ( err ){
            console.log( err );
        }

    });



    /*
    **
    **  swap it and 
    **  save new params.json
    **
    */
    params_json.body = source_body;
    fs.writeFile( './params.json', JSON.stringify( params_json ), function( err ){

        if ( err ){
            console.log( err );
        }

    });


});





