<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\Sensor;
use DB;

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

    public function index()
    {
        $data['totalSensor'] = collect(DB::select('
                                SELECT 
                                COUNT(*) total,
                                SUM(IF(VALUE=0, 1, 0)) AS total_parkir_kosong,
                                SUM(IF(VALUE=1, 1, 0)) AS total_parkir_terisi
                                from sensors
                            '))->first();

        return view('parkir')->with($data);
    }

    public function data()
    {
        $data = collect(DB::select('
                                SELECT 
                                COUNT(*) total,
                                SUM(IF(VALUE=0, 1, 0)) AS total_parkir_kosong,
                                SUM(IF(VALUE=1, 1, 0)) AS total_parkir_terisi
                                from sensors
                            '))->first();
                            
        return response()->json($data, $code ?? 200);
    }
}
