<?php

namespace Database\Seeders;

use Illuminate\Database\Console\Seeds\WithoutModelEvents;
use Illuminate\Database\Seeder;
use App\Models\Sensor;

class SensorSeeder extends Seeder
{
    /**
     * Run the database seeds.
     */
    public function run(): void
    {
        //
        Sensor::create(['name'=>'sensor1','value'=>0]);
        Sensor::create(['name'=>'sensor2','value'=>0]);
        Sensor::create(['name'=>'sensor3','value'=>0]);
        Sensor::create(['name'=>'sensor4','value'=>0]);
        Sensor::create(['name'=>'sensor5','value'=>0]);
        Sensor::create(['name'=>'sensor6','value'=>0]);
    }
}
