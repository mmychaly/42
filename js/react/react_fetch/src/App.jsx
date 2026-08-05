import { useState } from 'react'
import Users from './User';
import RequestPost from './RequestPost';
import RequestPut from './RequestPut'
import RequestDelete from './RequestDelete'

function App() {
    return ( <>
                <div style={{marginBottom:"16px"}}>
                    <RequestPost/>
                </div>
                <div style={{marginBottom:"16px"}}>
                    <RequestPut/>
                </div>
                <RequestDelete />
    </>);
}

export default App
