<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;

class ApiController extends Controller
{
	public function getJsonResponse(){
		$data = [
			'timestamp' => now (),
			'message' => 'Hello World',	
		];
		return response()->json($data);
	}
	public function getHelloWorld()
	{
		return view ('hello');
	}
    //
}
