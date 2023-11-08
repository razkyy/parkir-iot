<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\Sensor;

class SensorController extends Controller
{

    public function store(Request $request)
    {
        //
        for($i=1;$i<7;$i++)
        {
            $name = 'sensor'.$i;
            Sensor::where('name',$name)->update(['value'=>$request->$name]);

        }

        return 'berhasil';

    }
}
