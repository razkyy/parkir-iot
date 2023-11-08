<table class="table table-bordered">
    <thead>
      <tr>
        <th style="width: 10px">No</th>
        <th>Nama</th>
        <th>Status</th>
        <th>Keterangan</th>
      </tr>
    </thead>
    <tbody>
        @foreach($listSensor as $sensor)
            <tr>
                <td>
                    {{$loop->index + 1}}
                </td>
                <td>{{$sensor->name}}</td>
                <td width="100px">
                    @if($sensor->value == 0)
                        <span class="text-success"><h1><i class="fas fa-car"></i></h1></span>
                    @else 
                        <span class="text-danger"><h1><i class="fas fa-car"></i></h1></span>
                    @endif
                </td>
                <td width="100px">
                    @if($sensor->value == 0)
                        <span class="text-success">Terisi</span>
                    @else 
                        <span class="text-danger">Kosong</span>
                    @endif
                </td>
            </tr>
        @endforeach
    </tbody>
</table> 