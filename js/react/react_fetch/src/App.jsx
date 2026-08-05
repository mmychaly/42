import { useState } from 'react'
import Users from './User';
import RequestPost from './RequestPost';
import RequestPut from './RequestPut'

function App() {
    return ( <>
                <div style={{marginBottom:"16px"}}>
                    <RequestPost/>
                </div>
                <RequestPut />
    </>);
}

export default App
